<?php
/**
*   Twitter API wrapper
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

    require_once ('./error_raiser.inc');   
    require_once ('./rest_client.inc');
    require_once ('twitter_errors.inc');

//    twitter.inc Configuration 

    if (!$config) {
        $config = array ();
    }

    $config['TWITTER_URL'] = 'http://twitter.com/';
    $config['TWITTER_SEARCH_API'] = 'http://search.twitter.com/';

    class Twitter extends ErrorRaiser
    {
        private $_Username;
        private $_Password;
        private $_LastQuery;
        private $_Format = JSON;
        
        private $_Connection;
        
        private $_FormatAliases = array (JSON=>'json', XML=>'xml', ATOM=>'atom', RSS=>'rss');
        
        /**
        * Initialize Twitter object
        * 
        * @param Username for authorization requests
        * @param Password
        * @param Format of response (only default JSON is supported yet)
        */                  
        function Init ($Username = '', $Password = '', $Format = JSON) {
            if ($Username && $Password) {
                $this->_Username = $Username;
                $this->_Password = $Password;
            }
            $_FormatAliases[$this->_Format] = $Format;
            $this->_FlushError();
        }
                       
        private function Method ($name, $subname, $type, $data, $need_authentification = true) {
            global $config;
            $url = $config['TWITTER_URL'].$name.($subname?'/'.$subname:'').'.'.$this->_FormatAliases[$this->_Format];
            $object = array ();
            if ($need_authentification) {
                $object = $this->_Connection->RequestAndDecode($url, $type, $data, array ('Username'=>$this->_Username, 'Password'=>$this->_Password));
            } else
            {
                $object = $this->_Connection->RequestAndDecode($url, $type, $data);
            }
            
            if (!$object) {
                $err = $this->_Connection->GetLastError();
                $this->_Error ($err['ErrNo'], $err['Message']);
                return 0;
            }
            return $object;
        }             

        private function _Search ($name, $data) {
            global $config; 
            $url = $config['TWITTER_SEARCH_API'].$name.'.'.$this->_FormatAliases[$this->_Format];
            $object = $this->_Connection->RequestAndDecode($url, GET, $data);
            if (!$object) {
                $err = $this->_Connection->GetLastError();
                $this->_Error ($err['ErrNo'], $err['Message']);
                return 0;
            }
            return $object;
        }     
        
        /**
        * Initialize Twitter object
        * 
        * @param Username for authorization requests
        * @param Password
        * @param Format of response (only default JSON is supported yet)
        */
        function __construct ($Username = '', $Password = '', $Format = JSON) {
            $this->_Connection = new RestClient ();
            $this->Init($Username, $Password, $Format);
        }       
        
//      The Twitter Search API Wrapper's source code, partically automatically generated using generate_api_methods.php         
      
        /**
        * Returns tweets that match a specified query.
        * 
        * @param The data will be passed as request parameters.
        * @return 0 if some error occured, response-object otherwise.
        */
        function Search ($data = "") {
             return $this->_Search ("search", $data);
        }

        /**
        * Returns the top ten topics that are currently trending on Twitter.  The response includes the time of the request, the name of each trend, and the url to the Twitter Search results page for that topic.
        * 
        * @param The data will be passed as request parameters.
        * @return 0 if some error occured, response-object otherwise.
        */
        function Trends ($data = "") {
             return $this->_Search ("trends", $data);
        }

        /**
        * Returns the current top 10 trending topics on Twitter.  The response includes the time of the request, the name of each trending topic, and query used on Twitter Search results page for that topic.
        * 
        * @param The data will be passed as request parameters.
        * @return 0 if some error occured, response-object otherwise.
        */
        function TrendsCurrent ($data = "") {
             return $this->_Search ("trends/current", $data);
        }

        /**
        * Returns the top 20 trending topics for each hour in a given day.
        * 
        * @param The data will be passed as request parameters.
        * @return 0 if some error occured, response-object otherwise.
        */
        function TrendsDaily ($data = "") {
             return $this->_Search ("trends/daily", $data);
        }

        /**
        * Returns the top 30 trending topics for each day in a given week.
        * 
        * @param The data will be passed as request parameters.
        * @return 0 if some error occured, response-object otherwise.
        */
        function TrendsWeekly ($data = "") {
             return $this->_Search ("trends/weekly", $data);
        }
        
//      The Twitter REST API Wrapper's source code, partically automatically generated using generate_api_methods.php 
        
        /**
        * Returns the 20 most recent statuses from non-protected users who have set a custom user icon. The public timeline is cached for 60 seconds so requesting it more often than that is a waste of resources.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesPublicTimeline ($data = "", $param = "") {
             return $this->Method ("statuses/public_timeline", $param, GET, $data, false);
        }

        /**
        * Returns the 20 most recent statuses, including retweets, posted by the authenticating user and that user's friends. This is the equivalent of /timeline/home on the Web.
        * Usage note: This home_timeline is identical to statuses/friends_timeline except it also contains retweets, which statuses/friends_timeline does not (for backwards compatibility reasons). In a future version of the API, statuses/friends_timeline will go away and be replaced by home_timeline.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesHomeTimeline ($data = "", $param = "") {
             return $this->Method ("statuses/home_timeline", $param, GET, $data);
        }

        /**
        * Returns the 20 most recent statuses posted by the authenticating user and that user's friends. This is the equivalent of /timeline/home on the Web.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesFriendsTimeline ($data = "", $param = "") {
             return $this->Method ("statuses/friends_timeline", $param, GET, $data);
        }

        /**
        * Returns the 20 most recent statuses posted from the authenticating user. It's also possible to request another user's timeline via the id parameter. This is the equivalent of the Web /<user> page for your own user, or the profile page for a third party.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesUserTimeline ($data = "", $param = "") {
             return $this->Method ("statuses/user_timeline", $param, GET, $data);
        }

        /**
        * Returns the 20 most recent mentions (status containing @username) for the authenticating user.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesMentions ($data = "", $param = "") {
             return $this->Method ("statuses/mentions", $param, GET, $data);
        }

        /**
        * Returns the 20 most recent retweets posted by the authenticating user.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesRetweetedByMe ($data = "", $param = "") {
             return $this->Method ("statuses/retweeted_by_me", $param, GET, $data);
        }

        /**
        * Returns the 20 most recent retweets posted by the authenticating user's friends.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesRetweetedToMe ($data = "", $param = "") {
             return $this->Method ("statuses/retweeted_to_me", $param, GET, $data);
        }

        /**
        * Returns the 20 most recent tweets of the authenticated user that have been retweeted by others.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesRetweetsOfMe ($data = "", $param = "") {
             return $this->Method ("statuses/retweets_of_me", $param, GET, $data);
        }

        /**
        * Returns a single status, specified by the id parameter below.  The status's author will be returned inline.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesShow ($data = "", $param = "") {
             return $this->Method ("statuses/show", $param, GET, $data);
        }

        /**
        * Updates the authenticating user's status.  Requires the status parameter specified below.  Request must be a POST.  A status update with text identical to the authenticating user's current status will be ignored to prevent duplicates.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesUpdate ($data = "", $param = "") {
             return $this->Method ("statuses/update", $param, POST, $data);
        }

        /**
        * Destroys the status specified by the required ID parameter.  The authenticating user must be the author of the specified status.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesDestroy ($data = "", $param = "") {
             return $this->Method ("statuses/destroy", $param, POST, $data);
        }

        /**
        * Retweets a tweet. Requires the id parameter of the tweet you are retweeting. Request must be a POST or PUT. Returns the original tweet with retweet details embedded.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesRetweet ($data = "", $param = "") {
             return $this->Method ("statuses/retweet", $param, POST, $data);
        }

        /**
        * Returns up to 100 of the first retweets of a given tweet.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesRetweets ($data = "", $param = "") {
             return $this->Method ("statuses/retweets", $param, GET, $data);
        }

        /**
        * Here will be description of this method
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function UsersShow ($data = "", $param = "") {
             return $this->Method ("users/show", $param, GET, $data, false);
        }

        /**
        * Returns a user's friends, each with current status inline. They are ordered by the order in which the user followed them, most recently followed first, 100 at a time. (Please note that the result set isn't guaranteed to be 100 every time as suspended users will be filtered out.) Use the cursor option to access older friends. With no user specified, request defaults to the authenticated user's friends. It's also possible to request another user's friends list via the id, screen_name or user_id parameter.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesFriends ($data = "", $param = "") {
             return $this->Method ("statuses/friends", $param, GET, $data);
        }

        /**
        * Returns the authenticating user's followers, each with current status inline.  They are ordered by the order in which they followed the user, 100 at a time. (Please note that the result set isn't guaranteed to be 100 every time as suspended users will be filtered out.) Use the cursor option to access earlier followers.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function StatusesFollowers ($data = "", $param = "") {
             return $this->Method ("statuses/followers", $param, GET, $data);
        }

        /**
        * Returns a list of the 20 most recent direct messages sent to the authenticating user.  The XML and JSON versions include detailed information about the sending and recipient users.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function DirectMessages ($data = "", $param = "") {
             return $this->Method ("direct_messages", $param, GET, $data);
        }

        /**
        * Returns a list of the 20 most recent direct messages sent by the authenticating user.  The XML and JSON versions include detailed information about the sending and recipient users.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function DirectMessagesSent ($data = "", $param = "") {
             return $this->Method ("direct_messages/sent", $param, GET, $data);
        }

        /**
        * Sends a new direct message to the specified user from the authenticating user. Requires both the user and text parameters. Request must be a POST. Returns the sent message in the requested format when successful.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function DirectMessagesNew ($data = "", $param = "") {
             return $this->Method ("direct_messages/new", $param, POST, $data);
        }

        /**
        * Destroys the direct message specified in the required ID parameter.  The authenticating user must be the recipient of the specified direct message.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function DirectMessagesDestroy ($data = "", $param = "") {
             return $this->Method ("direct_messages/destroy", $param, POST, $data);
        }

        /**
        * Allows the authenticating users to follow the user specified in the ID parameter.  Returns the befriended user in the requested format when successful.  Returns a string describing the failure condition when unsuccessful. If you are already friends with the user an HTTP 403 will be returned.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FriendshipsCreate ($data = "", $param = "") {
             return $this->Method ("friendships/create", $param, POST, $data);
        }

        /**
        * Allows the authenticating users to unfollow the user specified in the ID parameter.  Returns the unfollowed user in the requested format when successful.  Returns a string describing the failure condition when unsuccessful.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FriendshipsDestroy ($data = "", $param = "") {
             return $this->Method ("friendships/destroy", $param, POST, $data);
        }

        /**
        * Tests for the existence of friendship between two users. Will return true if user_a follows user_b, otherwise will return false.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FriendshipsExists ($data = "", $param = "") {
             return $this->Method ("friendships/exists", $param, GET, $data);
        }

        /**
        * Returns detailed information about the relationship between two users.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FriendshipsShow ($data = "", $param = "") {
             return $this->Method ("friendships/show", $param, GET, $data);
        }

        /**
        * Returns an array of numeric IDs for every user the specified user is following.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FriendsIds ($data = "", $param = "") {
             return $this->Method ("friends/ids", $param, GET, $data);
        }

        /**
        * Returns an array of numeric IDs for every user following the specified user.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FollowersIds ($data = "", $param = "") {
             return $this->Method ("followers/ids", $param, GET, $data);
        }

        /**
        * Returns an HTTP 200 OK response code and a representation of the requesting user if authentication was successful; returns a 401 status code and an error message if not.  Use this method to test if supplied user credentials are valid. Because this method can be a vector for a brute force dictionary attack to determine a user's password, it is limited to 15 requests per 60 minute period (starting from your first request).
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountVerifyCredentials ($data = "", $param = "") {
             return $this->Method ("account/verify_credentials", $param, GET, $data);
        }

        /**
        * Returns the remaining number of API requests available to the requesting user before the API limit is reached for the current hour. Calls to rate_limit_status do not count against the rate limit.  If authentication credentials are provided, the rate limit status for the authenticating user is returned.  Otherwise, the rate limit status for the requester's IP address is returned. Learn more about the REST API rate limiting.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountRateLimitStatus ($data = "", $param = "") {
             return $this->Method ("account/rate_limit_status", $param, GET, $data);
        }

        /**
        * Ends the session of the authenticating user, returning a null cookie.  Use this method to sign users out of client-facing applications like widgets.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountEndSession ($data = "", $param = "") {
             return $this->Method ("account/end_session", $param, POST, $data);
        }

        /**
        * Sets which device Twitter delivers updates to for the authenticating user.  Sending none as the device parameter will disable IM or SMS updates.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountUpdateDeliveryDevice ($data = "", $param = "") {
             return $this->Method ("account/update_delivery_device", $param, POST, $data);
        }

        /**
        * Sets one or more hex values that control the color scheme of the authenticating user's profile page on twitter.com.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountUpdateProfileColors ($data = "", $param = "") {
             return $this->Method ("account/update_profile_colors", $param, POST, $data);
        }

        /**
        * Updates the authenticating user's profile image. Note that this method expects raw multipart data, not a URL to an image.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountUpdateProfileImage ($data = "", $param = "") {
             return $this->Method ("account/update_profile_image", $param, POST, $data);
        }

        /**
        * Updates the authenticating user's profile background image.  Note that this method expects raw multipart data, not a URL to an image.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountUpdateProfileBackgroundImage ($data = "", $param = "") {
             return $this->Method ("account/update_profile_background_image", $param, POST, $data);
        }

        /**
        * Sets values that users are able to set under the "Account" tab of their settings page. Only the parameters specified will be updated.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function AccountUpdateProfile ($data = "", $param = "") {
             return $this->Method ("account/update_profile", $param, POST, $data, true);
        }

        /**
        * Returns the 20 most recent favorite statuses for the authenticating user or user specified by the ID parameter in the requested format.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function Favorites ($data = "", $param = "") {
             return $this->Method ("favorites", $param, GET, $data);
        }

        /**
        * Favorites the status specified in the ID parameter as the authenticating user. Returns the favorite status when successful.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FavoritesCreate ($data = "", $param = "") {
             return $this->Method ("favorites/create", $param, POST, $data, true);
        }

        /**
        * Un-favorites the status specified in the ID parameter as the authenticating user. Returns the un-favorited status in the requested format when successful.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function FavoritesDestroy ($data = "", $param = "") {
             return $this->Method ("favorites/destroy", $param, POST, $data);
        }

        /**
        * Enables device notifications for updates from the specified user.  Returns the specified user when successful.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function NotificationsFollow ($data = "", $param = "") {
             return $this->Method ("notifications/follow", $param, POST, $data);
        }

        /**
        * Disables notifications for updates from the specified user to the authenticating user.  Returns the specified user when successful.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function NotificationsLeave ($data = "", $param = "") {
             return $this->Method ("notifications/leave", $param, POST, $data);
        }

        /**
        * Blocks the user specified in the ID parameter as the authenticating user. Destroys a friendship to the blocked user if it exists. Returns the blocked user in the requested format when successful.  You can find out more about blocking in the Twitter Support Knowledge Base.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function BlocksCreate ($data = "", $param = "") {
             return $this->Method ("blocks/create", $param, POST, $data);
        }

        /**
        * Un-blocks the user specified in the ID parameter for the authenticating user.  Returns the un-blocked user in the requested format when successful. 
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function BlocksDestroy ($data = "", $param = "") {
             return $this->Method ("blocks/destroy", $param, POST, $data);
        }

        /**
        * Returns if the authenticating user is blocking a target user. Will return the blocked user's object if a block exists, and error with a HTTP 404 response code otherwise.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function BlocksExists ($data = "", $param = "") {
             return $this->Method ("blocks/exists", $param, GET, $data);
        }

        /**
        * Returns an array of user objects that the authenticating user is blocking.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function BlocksBlocking ($data = "", $param = "") {
             return $this->Method ("blocks/blocking", $param, GET, $data);
        }

        /**
        * Returns an array of numeric user ids the authenticating user is blocking.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function BlocksBlockingIds ($data = "", $param = "") {
             return $this->Method ("blocks/blocking/ids", $param, GET, $data);
        }

        /**
        * Returns the authenticated user's saved search queries.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function SavedSearches ($data = "", $param = "") {
             return $this->Method ("saved_searches", $param, GET, $data);
        }

        /**
        * Retrieve the data for a saved search owned by the authenticating user specified by the given id.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function SavedSearchesShow ($data = "", $param = "") {
             return $this->Method ("saved_searches/show", $param, GET, $data);
        }

        /**
        * Creates a saved search for the authenticated user.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function SavedSearchesCreate ($data = "", $param = "") {
             return $this->Method ("saved_searches/create", $param, POST, $data);
        }

        /**
        * Destroys a saved search for the authenticated user. The search specified by id must be owned by the authenticating user.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function SavedSearchesDestroy ($data = "", $param = "") {
             return $this->Method ("saved_searches/destroy", $param, POST, $data);
        }

        /**
        * Allows a Consumer application to obtain an OAuth Request Token to request user authorization. This method fulfills Secion 6.1 of the OAuth 1.0 authentication flow.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function OauthRequestToken ($data = "", $param = "") {
             return $this->Method ("oauth/request_token", $param, GET, $data, false);
        }

        /**
        * Allows a Consumer application to use an OAuth Request Token to request user authorization. This method fulfills Secion 6.2 of the OAuth 1.0 authentication flow. Desktop applications must use this method (and cannot use oauth/authenticate).
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function OauthAuthorize ($data = "", $param = "") {
             return $this->Method ("oauth/authorize", $param, GET, $data, false);
        }

        /**
        * Allows a Consumer application to use an OAuth request_token to request user authorization. This method is a replacement fulfills Secion 6.2 of the OAuth 1.0 authentication flow for applications using the Sign in with Twitter authentication flow. The method will use the currently logged in user as the account to for access authorization unless the force_login parameter is set to true.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function OauthAuthenticate ($data = "", $param = "") {
             return $this->Method ("oauth/authenticate", $param, GET, $data, false);
        }

        /**
        * Allows a Consumer application to exchange the OAuth Request Token for an OAuth Access Token. This method fulfills Secion 6.3 of the OAuth 1.0 authentication flow.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function OauthAccessToken ($data = "", $param = "") {
             return $this->Method ("oauth/access_token", $param, POST, $data, false);
        }                                                 
        
        /**
        * Allows a Consumer application to exchange the OAuth Request Token for an OAuth Access Token. This method fulfills Secion 6.3 of the OAuth 1.0 authentication flow.
        * 
        * @param The data will be passed as request parameters.
        * @param Request parameter, passed in URI.
        * @return 0 if some error occured, response-object otherwise.
        */
        function HelpTest ($data = "", $param = "") {
             return $this->Method ("help/test", $param, GET, $data, false);
        }  
    };
?>