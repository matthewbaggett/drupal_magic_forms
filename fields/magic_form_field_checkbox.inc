<?php

class magic_form_field_checkbox extends magic_form_field {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.checkbox.phtml", $view);
  }
  /**
   * @param $value
   *
   * @return magic_form_field
   */
  public function set_value($value) {
    if($value == "on"){
      $this->value = true;
    }elseif($value == "off"){
      $this->value = false;
    }else{
      $this->value = $value;
    }
    return $this;
  }
}