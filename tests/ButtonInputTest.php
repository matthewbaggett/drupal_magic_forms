<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class ButtonInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_button_field';
        $this->input_default_label = 'Test button field';
    }

    public function testButtonInput()
    {
        //Create Text Input
        $new_field = magic_form_field_button::factory($this->input_default_name, $this->input_default_label, 2);
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Button Input
        $test_button_field = $form->find("input[name=".$this->input_default_name."]")[0];

        //Check Button Field
        $this->assertEquals("button", $test_button_field->attr['type'], "Type Equals button");
    }
    public function testButtonInputLabel()
    {
        //Create Text Input
        $new_field = magic_form_field_button::factory($this->input_default_name, null, 2);
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Button Input
        $test_button_field = $form->find("input[name=".$this->input_default_name."]")[0];

        //Check Button Field
        $this->assertEquals("button", $test_button_field->attr['type'], "Type Equals button");
    }
}
