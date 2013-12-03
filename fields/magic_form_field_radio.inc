<?php

class magic_form_field_radio extends magic_form_field_multi
{

    protected $labels = 'after';

    public function set_labels_before()
    {
        $this->labels = 'before';
        return $this;
    }

    public function set_labels_after()
    {
        $this->labels = 'after';
        return $this;
    }

    public function is_label_after()
    {
        if ($this->labels == 'after') {
            return TRUE;
        }
        return FALSE;
    }

    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return $this->render("form.radio.phtml", $view);
    }
}