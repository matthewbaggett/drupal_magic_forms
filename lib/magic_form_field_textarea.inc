<?php

class magic_form_field_textarea extends magic_form_field_text {

  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return magic_forms_template_view("form.textarea.phtml", $view);
  }
}