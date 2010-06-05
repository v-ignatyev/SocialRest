<?php
/**
* After executing this script, you can see new followed users in your account on Twitter.com!
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

  require_once ('twitter/twitter.inc');
  
  $T = new Twitter('Username','Password');
  
  $tosearch = 'coding';            // string to search
  
  $result = $T->Search(array('q'=>$tosearch));
  
  if (!$result) {
      $err = $T->GetLastError();
      echo ("ErrCode: {$err['ErrNo']}\n\nMessage: {$err['Message']}");
  }   
                        
  $users_to_follow = array ();

  foreach ($result->results as $record) {  
        array_push ($users_to_follow, $record->from_user);
  }
  
  foreach ($users_to_follow as $user) {
      
      $result = $T->UsersShow(array('screen_name'=>$user));     
      $id = $result->id;
      $screen_name = $result->screen_name;
      $result = $T->FriendshipsCreate(array ('follow'=>'true'), $screen_name);
  } 
?>
