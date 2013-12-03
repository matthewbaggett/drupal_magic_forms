<?php

class magic_form_field_textarea extends magic_form_field_text
{

    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return $this->render("form.textarea.phtml", $view);
    }
}