<?php

class magic_form_field_button extends magic_form_field {

  public static function factory($name = null, $label = null, $value = null) {
    $class = get_called_class();
    if($label === null){
      $label = $name;
    }
    $instance = new $class($name, $label);
    return $instance;
  }

  public function __construct($name = null, $label = null) {
    $this->name = $name;
    $this->label = t($label);
  }

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.button.phtml", $view);
  }
}