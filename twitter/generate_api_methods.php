<?php
/**
*  This code generates PHP-code for RESTful functions of Twitter REST and Search APIs, parsing the search_api_methods.txt and 
*  rest_api_methods.txt files, that contains strings with method names.
*  
*  Actually, this is not DRY. Please, don't kick me!
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

// simply load the API methods names
$ff = fopen ('search_api_methods.txt', 'r');
$aa = array ();

// open a file for dumping automatically generated code
$f2 = fopen ('twitter.inc.auto', 'w');

// open a file, which contains some "header" code
$f3 = fopen ('twitter.inc.pre', 'r');
while (!feof ($f3)) {
    fwrite ($f2, fgets($f3));   //...and copy it's content to twitter.inc.auto
}
fclose ($f3);
    
fwrite($f2, "\n\n//      The Twitter Search API Wrapper's source code, partically automatically generated using generate_api_methods.php \n\n");    
                                    
// reading API methods names 
while (!feof ($ff)) {
    array_push($aa, fgets($ff));
}                     
// parse input strings to make a Camel-style method names in code
foreach ($aa as $s) {
    $s = trim ($s);
    $names = explode ('/',$s);
    $thename = "";
    foreach ($names as $aname) {
        $names1_sub = explode ('_', $aname);
        $name1 = "";
        foreach ($names1_sub as $name1_sub) {
            $name1 .= ucfirst($name1_sub);
        }
        $thename .= $name1;
    }
                  
// writes the "body" of automatically generated source code                  
    fwrite($f2, "\t/**\n");
    fwrite($f2, "\t* Here will be description of this method\n");
    fwrite($f2, "\t* \n");
    fwrite($f2, "\t* @param ".'$data'." The data will be passed as request parameters.\n");
    fwrite($f2, "\t* @return 0 if some error occured, response-object otherwise.\n");
    fwrite($f2, "\t*/\n");
    fwrite($f2, "\tfunction $thename (".'$data = ""'.") {\n");
    fwrite($f2, "\t".'     return $this->_Search ("'.$s.'", $data);'."\n");
    fwrite($f2, "\t".'}'."\n\n");
}    

// simply load the API methods names
$f = fopen ('rest_api_methods.txt', 'r');
$a = array ();

// reading API methods names 
while (!feof ($f)) {
    array_push($a, fgets($f));
}                  

fwrite($f2, "\n\n//      The Twitter REST API Wrapper's source code, partically automatically generated using generate_api_methods.php \n\n");       

// parse input strings to make a Camel-style method names in code
foreach ($a as $s) {
    $s = trim ($s);
    $names = explode ('/',$s);
    $thename = "";
    foreach ($names as $aname) {
        $names1_sub = explode ('_', $aname);
        $name1 = "";
        foreach ($names1_sub as $name1_sub) {
            $name1 .= ucfirst($name1_sub);
        }
        $thename .= $name1;
    }
                  
// writes the "body" of automatically generated source code                  
    fwrite($f2, "\t/**\n");
    fwrite($f2, "\t* Here will be description of this method\n");
    fwrite($f2, "\t* \n");
    fwrite($f2, "\t* @param ".'$data'." The data will be passed as request parameters.\n");
    fwrite($f2, "\t* @param ".'$param'." Request parameter, passed in URI.\n");
    fwrite($f2, "\t* @return 0 if some error occured, response-object otherwise.\n");    
    fwrite($f2, "\t*/\n");
    fwrite($f2, "\tfunction $thename (".'$data = ""'.", ".'$param = ""'.") {\n");
    fwrite($f2, "\t".'     return $this->Method ("'.$s.'", $param, GET, $data, false);'."\n");
    fwrite($f2, "\t".'}'."\n\n");
}     

// write the "footer" of automatically generated source code
$f3 = fopen ('twitter.inc.post', 'r');
while (!feof ($f3)) {
    fwrite ($f2, fgets($f3));
}

?>
