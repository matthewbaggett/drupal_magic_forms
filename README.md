Objective Forms
==================

A slightly less hateful implementation of form handling for Drupal.

Because we all know drupal forms blow.

Support many form field types:
 * Button
 * File
 * Group
 * Hidden
 * Input
 * Radios
 * Select
 * Textarea

Bonus features:
 * Data Tables.
 * Labels

Validators
=========

Example with validators:

    $form = new magic_form('my-form');
    $form
      ->add_field(
        magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
          ->add_validator(new magic_form_validator_is_valid_phonenumber())
          ->add_validator(new magic_form_validator_is_valid_email())
      )->add_field(
        magic_form_field_text::factory('other-field')
          ->add_validator(new magic_form_validator_is_less_than(100))
          ->add_validator(new magic_form_validator_is_greater_than(50))
      )->add_field(
        magic_form_field_text::factory('other-field')
          ->add_validators(
            new magic_form_validator_is_less_than(100),
            new magic_form_validator_is_greater_than(50),
            new magic_form_validator_regexp('REGEXP_GOES_HERE')
          )
      )->add_fields(
        magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
          ->add_validator(new magic_form_validator_is_valid_phonenumber())
          ->add_validator(new magic_form_validator_is_valid_email()),
        magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
          ->add_validator(new magic_form_validator_is_valid_phonenumber())
          ->add_validator(new magic_form_validator_is_valid_email()),
        magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
          ->add_validator(new magic_form_validator_is_valid_phonenumber())
          ->add_validator(new magic_form_validator_is_valid_email()),
        magic_form_field_text::factory('some-field', 'Some Field', 'Some Default')
          ->add_validator(new magic_form_validator_is_valid_phonenumber())
          ->add_validator(new magic_form_validator_is_valid_email())
      );