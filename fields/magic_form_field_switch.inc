<?php

class magic_form_field_switch extends magic_form_field {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.switch.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
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