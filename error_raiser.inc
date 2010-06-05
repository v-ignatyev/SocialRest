<?php
    if (!$errors) {
        $errors = array ();
    }
          
    class ErrorRaiser
    {
        protected $_ErrNo;
        protected $_ErrMessage; 
        
        protected function _Error ($code, $message = '') {
            $this->_ErrNo = $code;
            $this->_ErrMessage = $message;
        }

        protected function _FlushError () {
            $this->_Error (0, '');
        }
        
        /**
        * Returns last error as associated array:
        * 'ErrNo' => error code
        * 'Message' => error message
        */
        public function GetLastError () {    
            return array ('ErrNo'=>$this->_ErrNo, 'Message'=>$this->_ErrMessage);
        }
    };
?>