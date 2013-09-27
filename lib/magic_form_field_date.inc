<?php

class magic_form_field_date extends magic_form_field_text{

  /**
   * Sanitise the date given
   * @return string
   */
  public function get_value(){
    return date("Y-m-d H:i:s", strtotime(parent::get_value()));
  }
}