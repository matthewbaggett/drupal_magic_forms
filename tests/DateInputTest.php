<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class DateInputTest extends PHPUnit_Framework_TestCase {

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp(){
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_text_field';
        $this->input_default_label = 'Test text field';
    }

    public function testDateInput()
    {
        //Create Text Input
        $new_field = magic_form_field_date::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_support_time(true)
        ->set_support_date(true);

        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=".$this->input_default_name."]")[0];

        //Check Text Field
        $this->assertEquals("text", $test_text_field->attr['type'], "Type Equals Text");
        $this->assertEquals($this->input_default_name, $test_text_field->attr['name'], "Name Equals ".$this->input_default_name);

        //Check set_label
        $test_test_field_label = $form->find("label[for=".$this->input_default_name."]")[0];
        $this->assertEquals($this->input_default_name, $test_test_field_label->attr['for'], "Check Label");
        $this->assertEquals($this->input_default_label, $test_test_field_label->innertext(), "Check Label Text");
    }

    public function testDateTable()
    {
        //Create Text Input
        $new_field = magic_form_field_date::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_support_time(true)
            ->set_support_date(true);

        $table = $new_field->draw_calendar(12,2014,null);
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=".$this->input_default_name."]")[0];

        //Check Text Field
        $this->assertEquals("text", $test_text_field->attr['type'], "Type Equals Text");
        $this->assertEquals($this->input_default_name, $test_text_field->attr['name'], "Name Equals ".$this->input_default_name);

        //Check set_label
        $test_test_field_label = $form->find("label[for=".$this->input_default_name."]")[0];
        $this->assertEquals($this->input_default_name, $test_test_field_label->attr['for'], "Check Label");
        $this->assertEquals($this->input_default_label, $test_test_field_label->innertext(), "Check Label Text");
    }
}

