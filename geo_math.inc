<?php
/**
* This file contains functions to operate with geodata.
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

  define ('AVERAGE_GREAT_CIRCLE_RADIUS', 6372795);
  
  /**
  * Degrees to Radians conversion
  */
  function DegToRad ($x) {
      return $x*pi()/180;
  }
  
  /**
  * Radians to Degrees conversion
  */  
  function RadToDeg ($x) {
      return $x*180/pi();
  }
            
  /**
  * Degrees Minutes Seconds to Float conversion
  */  
  function DegMinSecToFloat ($deg, $min = 0, $sec = 0) {
      return $deg + $min/60 + $sec/3600;
  }
  
  /**
  * Returns the distance in kilometers between two points, defined as an array [Lat1;Lon1] and [Lat2;Lon2]
  */
  function GetDistance ($x1, $x2) {
      return (AVERAGE_GREAT_CIRCLE_RADIUS * _AngleDelta($x1, $x2))/1000;
  }          
  
  /**
  * Difference in angles between two points, defined in LatLon format
  */
  function _AngleDelta ($x1, $x2) {
      return acos(sin(DegToRad($x1[0]))*sin(DegToRad($x2[0]))+cos(DegToRad($x1[0]))*cos(DegToRad($x2[0]))*cos(abs(DegToRad($x1[1])-DegToRad($x2[1]))));
  }
?>