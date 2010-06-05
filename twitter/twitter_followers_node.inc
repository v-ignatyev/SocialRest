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

require_once ('twitter.inc');
require_once ('./tree_node.inc');         
require_once ('twitter_followers_node_errors.inc');         

  class TwitterFollowersNode extends TreeNode 
  {
      private function _FollowersRecurse ($cursor, $user, &$T) {
          $response = $T->StatusesFollowers ($cursor?array('cursor'=>$cursor):array('cursor'=>'-1'), $user);
          
//          var_dump($response);
          
//          var_dump($response);
          if (!$response) {
              return;
          }
          
          foreach ($response->users as $follower) {
              $this->AddChild(new TwitterFollowersNode($follower, $this));
          }
          
          if ($response->next_cursor==0 || count($response->users)==0) {
              return;
          }                   
          $this->_FollowersRecurse($response->next_cursor, $user, $T);
      }
      
      function Generate ($user, &$T, &$parent = 0) {
          global $errors;
          
          $this->_Parent = &$parent;
          $this->Data = $T->UsersShow (0, $user);
          
          if (!$this->Data) {                                      
              $this->_Error('E_TWIT_USER', $errors['E_TWIT_USER']);
              return 0;
          }
          
          return $this->_FollowersRecurse('-1', $user, $T);
          
/*          $request = $T->StatusesFollowers (0, $user);
          
          foreach ($request->users_list->users as $user) {
              
          }*/
      }
  }
  
  /*
  <?php
  require_once ('twitter.inc');
  require_once ('./tree_node.inc');
                        /*
  class TwitterFollowersGraph 
  {       
      private $_TheT;
      private $_TheUser;
      private $_TheTree;
      
      function WhichUser () {
          return $this->_TheUser;
      }
      
      function __construct (&$T, $user) {
        $this->TheT = &$T;
        $this->_TheUser = $user;                            
      }
      
      function GenerateGraph () {
        if ($this->_TheTree) {
            return $this->_TheTree;
        }                
        $this->_TheTree = new TreeNode(array('user'=>$user));
        $this->_TheT->
      }
      
      function GetTree () {
        return $this->_TheTree;
      }
  }                   
                            
?> 
  */
?>