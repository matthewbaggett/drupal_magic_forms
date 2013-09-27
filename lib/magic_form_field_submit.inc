<?php

class magic_form_field_submit extends magic_form_field_button{
    public function __toString(){
        $view = new StdClass();
        $view->field = $this;
        return magic_forms_template_view("form.submit.phtml", $view);
    }


}