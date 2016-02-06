<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class SwitchInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'switch';
        $this->input_default_label = 'Test switch field';
    }

    public function testSwitchInput()
    {
        $new_field = new magic_form_field_switch($this->input_default_name, $this->input_default_label);
        $new_field->set_value("test");
        $this->magic_form->add_fields($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Radio Inputs
        $test_checkbox_field1 = $form->find("input[id=".$this->input_default_name."]")[0];

        //Check Radio Inputs
        $this->assertEquals($this->input_default_name.'', $test_checkbox_field1->attr['name'], "Checkbox Name Equals ".$this->input_default_name);
    }

    public function testSwitchInputOn()
    {
        $new_field = new magic_form_field_switch($this->input_default_name, $this->input_default_label);
        $new_field->set_value("on");
        $this->magic_form->add_fields($new_field);
        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Radio Inputs
        $test_checkbox_field1 = $form->find("input[id=".$this->input_default_name."]")[0];

        //Check Radio Inputs
        $this->assertEquals($this->input_default_name.'', $test_checkbox_field1->attr['name'], "Checkbox Name Equals ".$this->input_default_name);
    }
    public function testSwitchInputOff()
    {
        $new_field = new magic_form_field_switch($this->input_default_name, $this->input_default_label);
        $new_field->set_value("off");
        $this->magic_form->add_fields($new_field);
        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Radio Inputs
        $test_checkbox_field1 = $form->find("input[id=".$this->input_default_name."]")[0];

        //Check Radio Inputs
        $this->assertEquals($this->input_default_name.'', $test_checkbox_field1->attr['name'], "Checkbox Name Equals ".$this->input_default_name);
    }
}
