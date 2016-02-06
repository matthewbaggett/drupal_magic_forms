<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class FileFieldInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_file_field_field';
        $this->input_default_label = 'Test file field field';
    }

    public function testFileFieldInput()
    {
        //Create Text Input
        $new_field = magic_form_field_file::factory($this->input_default_name, $this->input_default_label);

        $hasfile = $new_field->has_file();

        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_hidden_field = $form->find("input[name=".$this->input_default_name."]")[0];

        //Check Text Field
        $this->assertEquals("file", $test_hidden_field->attr['type'], "Type Equals File");
        $this->assertEquals($this->input_default_name, $test_hidden_field->attr['name'], "Name Equals ".$this->input_default_name);
    }
}
