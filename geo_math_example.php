<?php
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
  require_once ('yahoo/yahoo_geo_coding.inc');
  require_once ('geo_math.inc');
  
  $Y = new YahooGeoCoding();                                                                                            
  
  $r = $Y->Request(array ('zip'=>'111033', 'state'=>'Russia'));
  $Yandex = array ($r['ResultSet']['Result']['Latitude'], $r['ResultSet']['Result']['Longitude']);
  
  $r = $Y->Request(array ('zip'=>'10011', 'state'=>'NY')); 
  $Google = array ($r['ResultSet']['Result']['Latitude'], $r['ResultSet']['Result']['Longitude']);
  
  $Distance = GetDistance ($Google, $Yandex);
  
  echo ("<p>The distance between Yandex Office in Moscow and Google office in NY is <b>$Distance kilometers</b></p>");
?>
