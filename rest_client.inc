<?php
/**
*   This code gives ability to perform GET and POST requests for RESTful webservices
*   using native fopen and cURL library.
* 
*   Note: it is very simple!
* 
*   @author vladimir.ignatyev@ridev.ru
*/

/*
Copyright (c) 2009 Vladimir Ignatyev & Ridev corp., http://www.ridev.ru/

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE. 
*/

    require_once ('rest_client_errors.inc');
    require_once ('error_raiser.inc');
    
// rest_client.inc Configuration 

    if (!$config) {
        $config = array ();
    }

    $config['CURL_TIMEOUT'] = 30;    // timeout
    
    if (!defined ('GET')) { define ('GET', 0); }
    if (!defined ('POST')) { define ('POST', 1); }
    
    if (!defined ('JSON')) { define ('JSON', 0); }
    if (!defined ('XML')) { define ('XML', 1); }
    if (!defined ('ATOM')) { define ('ATOM', 2); }
    if (!defined ('RSS')) { define ('RSS', 3); }
    if (!defined ('PHPSERIALIZED')) { define ('PHPSERIALIZED', 4); }

    class RestClient extends ErrorRaiser
    {        
        private $_Format = JSON;
        
        /**
        * Generates the string after http://www.site.com/... for GET request
        * 
        * @param Array of key-value pairs, that are parameters for request
        */    
        private function PreparePairsForHTTP (&$pairs) {
            if ($pairs===0) { return ""; }
            
            $uri = "?";
            
            $first = true;
            foreach ($pairs as $key=>$value) {
                if (!$first) { 
                    $uri.='&';       
                }
                $uri.=urlencode($key).'='.urlencode($value);     
                $first = false;
            }
            
            return $uri;
        }    

        /**
        * Request data from REST-service. cURL used to retrieve data, no parsing will be applied.
        * 
        * @param URL to request for
        * @param Type of request (GET or POST)
        * @param array of key-value pairs, that are parameters for request
        * @param array ('user'=>$username, 'pass'=>$password) pair
        */    
        private function RESTRequest ($url, $type, $data = 0, $userpwdpair = 0) {
            global $config;
            global $errors;
            
            $ch = curl_init();
            if (!$url) {
                return 0;
            }
            
            $a = array (CURLOPT_URL => $url,
            CURLOPT_TIMEOUT => $config['CURL_TIMEOUT'],
            CURLOPT_RETURNTRANSFER => TRUE);
            $a[CURLOPT_HTTPHEADER] = array('Expect:');
            
            if ($type == GET) {
                $a[CURLOPT_URL] .= $this->PreparePairsForHTTP ($data);
                $a[CURLOPT_HTTPGET] = TRUE;
            } elseif ($type == POST) {
                $a[CURLOPT_POST] = TRUE;
                $a[CURLOPT_POSTFIELDS] = $data;
            } else {
                $this->_Error ('E_REST_NOT_SUPPORTED',$errors['E_REST_NOT_SUPPORTED']);
                return 0;
            }
                                       
            if ($userpwdpair) {
                $a[CURLOPT_HTTPAUTH] = CURLAUTH_BASIC;
                $a[CURLOPT_USERPWD] = $userpwdpair['Username'].':'.$userpwdpair['Password'];
            }
            curl_setopt_array($ch, $a);
            $content = curl_exec($ch);

            if (!$content) {                              
                $this->_Error (curl_errno($ch),'cURL: '.curl_error($ch));
            }                  
            

            curl_close($ch);

            return $content;
        }

        /**
        * Requests data from REST-service and decodes it (JSON only).
        * 
        * @param URL to request for 
        * @param Type of request (GET or POST)
        * @param Array of key-value pairs, that are parameters for request        * 
        * @param Array ('user'=>$username, 'pass'=>$password) pair
        */    
        public function RequestAndDecode ($url, $type, $data = 0,  $userpwdpair = 0) {
            global $errors;

            $content = $this->Request( $url, $type, $data,  $userpwdpair);
            
            if (!$content) {
                return 0;
            }
                        
            if ($this->_Format == JSON) {
                return json_decode($content);
            } elseif ($this->_Format == PHPSERIALIZED) {
                return unserialize($content);
            }
            
            $this->_Error ('E_REST_NOT_SUPPORTED', $errors['E_REST_NOT_SUPPORTED']);
                        
            return 0;
        }

        /**
        * Requests data from REST-service without decoding.
        * 
        * @param Type of request: 'get' or 'rest'
        * @param URL to request for
        * @param Array of key-value pairs, that are parameters for request        * 
        * @param Array ('user'=>$username, 'pass'=>$password) pair
        */               
        public function Request ($url, $type = GET ,$data = 0,  $userpwdpair = 0) {
            return $this->RESTRequest($url, $type, $data, $userpwdpair);
        }
                        
        function __construct ($Format = JSON) {
            $this->_Format = $Format;
            $this->_FlushError();            
        }
    };
?>