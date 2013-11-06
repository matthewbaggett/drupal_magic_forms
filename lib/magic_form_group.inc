<?php

class magic_form_group extends magic_form_item
{
    private $fields;
    private $group_name;
    private $group_label;

    public function __construct($group_name = null, $group_label = null)
    {
        $this->set_group_name($group_name);
        $this->set_group_label($group_label);

        // Support legacy behaviour
        if($group_label === null && $group_name !== null){
            $this->set_group_label($group_name);
        }
    }

    public function add_field(magic_form_item $field)
    {
        $field->set_scope($this->get_scope());
        $this->fields[$field->get_name()] = $field;
        return $this;
    }

    public function get_fields()
    {
        return $this->fields;
    }

    public function set_group_name($group_name){
        $this->group_name = $group_name;
        return $this;
    }

    public function get_group_name()
    {
        return $this->group_name;
    }

    public function set_group_label($group_label){
        $this->group_label = $group_label;
        return $this;
    }

    public function get_group_label()
    {
        return t($this->group_label);
    }

    public function __toString()
    {
        $view = new StdClass();
        $view->field = $this;
        return $this->render("form.group.phtml", $view);
    }

    public function get_name()
    {
        return $this->get_group_name();
    }

    static public function factory($group_name = null)
    {
        return new magic_form_group($group_name);
    }

    public function add_fields()
    {
        foreach (func_get_args() as $argument) {
            $this->add_field($argument);
        }
        return $this;
    }
}