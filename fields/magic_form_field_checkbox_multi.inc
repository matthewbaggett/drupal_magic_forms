<?php

class magic_form_field_checkbox_multi extends magic_form_field_multi {
  public function __toString() {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.checkbox_multi.phtml", $view, $this->get_scope() instanceof magic_form ? $this->get_scope()->get_templates_directory(): 'templates');
  }

  public function get_value(){
    if(parent::get_value() === null){
      return array();
    }else{
      return parent::get_value();
    }
  }
}