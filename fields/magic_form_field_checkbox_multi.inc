<?php

class magic_form_field_checkbox_multi extends magic_form_field_multi {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.checkbox_multi.phtml", $view);
  }
}