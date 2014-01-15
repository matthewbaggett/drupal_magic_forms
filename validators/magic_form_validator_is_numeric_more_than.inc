<?php

class magic_form_validator_is_numeric_more_than extends magic_form_validator implements magic_form_validator_interface {

  private $limit = 0;

  public function test($data) {
    $this->limit = $this->get_param(0);
    if(!is_numeric($data)){
      return false;
    }
    if($data > $this->limit){
      return true;
    }
    return false;
  }

  public function user_friendly_failure_message($message_params) {
    return t(
      "Number too small. Must be more than :limit",
      array_merge(
        $message_params,
        array(
          ':limit' => $this->limit,
        )
      )
    );
  }
}

