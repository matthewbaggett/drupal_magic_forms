<?php

class magic_form_field_select extends magic_form_field_multi {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return magic_forms_template_view("form.select.phtml", $view);
  }
}