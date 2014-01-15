<?php

class magic_form_validator_is_length_less_than extends magic_form_validator implements magic_form_validator_interface {

  private $data_length = 0;

  public function test($data) {
    $data = $this->sanitise($data);
    $this->data_length = strlen($data);
    return $this->data_length < $this->get_param(0);
  }

  public function user_friendly_failure_message($message_params) {
    return t(
      "Field :field_name content is too short. :length is :length_short_by characters too short.",
      array_merge(
        $message_params,
        array(
          ':length' => $this->data_length,
          ':length_short_by' => $this->get_param(1) - $this->data_length
        )
      )
    );
  }
}

