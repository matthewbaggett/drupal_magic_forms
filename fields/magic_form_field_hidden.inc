<?php

class magic_form_field_hidden extends magic_form_field_text {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.hidden.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates_bootstrap');
  }
}