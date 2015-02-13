<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class TextInputTest extends PHPUnit_Framework_TestCase {

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
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_attributes(array("testattribute" => "testattributevalue", "testattribute2" => "testattributevalue2"));
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check Text Field
        $this->assertEquals("text", $test_text_field->attr['type'], "Type Equals Text");
        $this->assertEquals("test_text_field", $test_text_field->attr['name'], "Name Equals test_text_field");

        //Check set_label
        $test_test_field_label = $form->find("label[for=test_text_field]")[0];
        $this->assertEquals("test_text_field", $test_test_field_label->attr['for'], "Check Label");
        $this->assertEquals("Test text field", $test_test_field_label->innertext(), "Check Label Text");

    }

    public function testTextInputAttributes()
    {
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_attributes(array("testattribute" => "testattributevalue", "testattribute2" => "testattributevalue2"));
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check Set Attributes
        $this->assertEquals("testattributevalue", $test_text_field->attr['testattribute'], "Check Attribute Name");
        $this->assertEquals("testattributevalue2", $test_text_field->attr['testattribute2'], "Check Attribute Value");
    }

    public function testTextInputSetLabel()
    {
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_label('testsetlabel');
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check set_label
        $test_test_field_label = $form->find("label[for=test_text_field]")[0];
        $this->assertEquals("test_text_field", $test_test_field_label->attr['for'], "Check set_label");
        $this->assertEquals("testsetlabel", $test_test_field_label->innertext(), "Check set_label Text");
    }

    public function testTextInputDisable()
    {
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->disable();
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check disable()
        $this->assertContains('disabled', $test_text_field->attr['class'], "Check Disable");
    }

    public function testTextInputAddClass()
    {
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->add_class('testnewclass');
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check add_class()
        $this->assertContains('testnewclass', $test_text_field->attr['class'], "Check Add Class");
    }

    public function testTextFactoryValue()
    {
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label, 'testsetdefaultvalue');
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check Value
        $this->assertContains('testsetdefaultvalue', $test_text_field->attr['value'], "Check Factory Value");
    }

    public function testTextSetValue()
    {
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label, 'testsetdefaultvalue');
        $new_field->set_value('testsetvalue');
        $this->magic_form->add_field($new_field);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Text Input
        $test_text_field = $form->find("input[name=test_text_field]")[0];

        //Check Value
        $this->assertContains('testsetvalue', $test_text_field->attr['value'], "Check Set Value");
    }
}

