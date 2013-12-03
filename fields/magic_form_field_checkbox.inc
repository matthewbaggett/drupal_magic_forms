<?php

class magic_form_field_checkbox extends magic_form_field {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.checkbox.phtml", $view);
  }
}