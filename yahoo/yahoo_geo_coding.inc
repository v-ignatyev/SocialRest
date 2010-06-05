<?php
/**
* Yahoo Geo Coding API Wrapper
* 
* @author vladimir.ignatyev@ridev.ru
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

require_once ('./rest_client.inc');
require_once ('./pure_error_raiser.inc');

    if (!$config) {
        $config = array ();
    }

    $config['YAHOO_GEOCODING_URL'] = 'http://local.yahooapis.com/MapsService/V1/geocode';    // Yahoo Geocoding API URL

  class YahooGeoCoding extends PureErrorRaiser
  {                                
      private $_Appid;
      
      /**
      * Perform a REST request to Yahoo Geocoding API
      * 
      * @param Array of $key=>$value pairs, that contains parameters for request (see http://developer.yahoo.com/ for more details)
      */      
      function Request ($params) {
          global $config;
          
          $p = $params;
          $p['output'] = 'php';
          $p['appid'] = $this->_Appid;                                          
          
          return $this->_Rest->RequestAndDecode($config['YAHOO_GEOCODING_URL'], GET, $p);
      }
      
      /**
      * Constructs the YahooGeoCoding class
      * 
      * @param GeoCoding API registered application Id (see http://developer.yahoo.com/ for more details)
      */
      function __construct ($app_id = 'YD-9G7bey8_JXxQP6rxl.fBFGgCdNjoDMACQA--') {
          $this->_Appid = $app_id;
          $this->_Rest = new RestClient(PHPSERIALIZED);
      }
  }
?>