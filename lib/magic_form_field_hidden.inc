<?php

class magic_form_field_hidden extends magic_form_field_text
{
  public function __toString()
  {
    $view = new StdClass();
    $view->field = $this;
    return $this->render("form.hidden.phtml", $view);
  }
}