<?php
/**
 * Created by PhpStorm.
 * User: jason.smart
 * Date: 13/02/2015
 * Time: 10:31
 */

class GroupInputTest extends PHPUnit_Framework_TestCase
{

    /** @var $magic_form magic_form */
    private $magic_form;

    public function setUp()
    {
        $this->magic_form = new magic_form();
        $this->magic_form->set_templates_directory("templates_bootstrap");

        //Set Some Vars
        $this->input_default_name = 'test_text_field';
        $this->input_default_label = 'Test text field';
    }

    public function testGroupInput()
    {

        $test_wrapper = magic_form_group::factory('Test Wrapper');
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_attributes(array("testattribute" => "testattributevalue", "testattribute2" => "testattributevalue2"));
        $test_wrapper->add_field($new_field);
        $this->magic_form->add_field($test_wrapper);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Form Group
        $test_group_field = $form->find("div[class=field-test-wrapper]")[0];

        //Check Group Field
        $this->assertContains("form-group", $test_group_field->attr['class'], "Type Contains Form Group");

        //Check Group Label
        $test_group_h3 = $test_group_field->find("h3")[0];
        $this->assertEquals("Test Wrapper", $test_group_h3->innertext(), "Check Label");
    }


    public function testGroupInputAddFields()
    {

        $test_wrapper = magic_form_group::factory('Test Wrapper');
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_attributes(array("testattribute" => "testattributevalue", "testattribute2" => "testattributevalue2"));
        $new_field2 = magic_form_field_text::factory($this->input_default_name."_2", $this->input_default_label."_2");
        $new_field2->set_attributes(array("testattribute" => "testattributevalue", "testattribute2" => "testattributevalue2"));
        $test_wrapper->add_fields($new_field, $new_field2);
        $this->magic_form->add_field($test_wrapper);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Form Group
        $test_group_field = $form->find("div[class=field-test-wrapper]")[0];

        //Check Group Field
        $this->assertContains("form-group", $test_group_field->attr['class'], "Type Contains Form Group");

        //Check Group Label
        $test_group_h3 = $test_group_field->find("h3")[0];
        $this->assertEquals("Test Wrapper", $test_group_h3->innertext(), "Check Label");
    }

    public function testGroupInputRemoveFields()
    {

        $test_wrapper = magic_form_group::factory('Test Wrapper');
        //Create Text Input
        $new_field = magic_form_field_text::factory($this->input_default_name, $this->input_default_label);
        $new_field->set_attributes(array("testattribute" => "testattributevalue", "testattribute2" => "testattributevalue2"));
        $new_field2 = magic_form_field_text::factory($this->input_default_name."_2", $this->input_default_label."_2");
        $new_field2->set_attributes(array("testattribute" => "testattributevalue", "testattribute2" => "testattributevalue2"));
        $test_wrapper->add_fields($new_field, $new_field2);
        $test_wrapper->remove_fields($new_field, $new_field2);
        $json = $test_wrapper->__toJsonArray();
        $this->magic_form->add_field($test_wrapper);

        $html = $this->magic_form->__toString();

        //Get HTML Dom
        $dom = str_get_html($html);
        $form = $dom->find("//form")[0];

        //Find Form Group
        $test_group_field = $form->find("div[class=field-test-wrapper]")[0];

        //Check Group Field
        $this->assertContains("form-group", $test_group_field->attr['class'], "Type Contains Form Group");

        //Check Group Label
        $test_group_h3 = $test_group_field->find("h3")[0];
        $this->assertEquals("Test Wrapper", $test_group_h3->innertext(), "Check Label");
    }
}
