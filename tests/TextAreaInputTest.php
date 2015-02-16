<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class TextAreaInputTest extends PHPUnit_Framework_TestCase {

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp(){
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_text_field';
        $this->input_default_label = 'Test text field';
    }

    public function testTextInput()
    {
        //Create Text Input
        $new_field = magic_form_field_textarea::factory($this->input_default_name, $this->input_default_label);
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("textarea[name=test_text_field]")[0];

        //Check Text Field
        $this->assertEquals("test_text_field", $test_text_field->attr['name'], "Name Equals test_text_field");

        //Check set_label
        $test_test_field_label = $form->find("label[for=test_text_field]")[0];
        $this->assertEquals("test_text_field", $test_test_field_label->attr['for'], "Check Label");
        $this->assertEquals("Test text field", $test_test_field_label->innertext(), "Check Label Text");

    }
}

