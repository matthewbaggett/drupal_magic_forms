<?php

class magic_form_validator_is_length_more_than extends magic_form_validator implements magic_form_validator_interface
{

    private $data_length = 0;

    public function test($data)
    {
        $data = $this->sanitise($data);
        $this->data_length = strlen($data);
        return $this->data_length > $this->get_param(0);
    }

    public function user_friendly_failure_message($message_params)
    {
        return t(
            "Field :field_name content is too long. :length is :length_long_by characters too long.",
            array_merge(
                $message_params,
                array(
                ':length' => $this->data_length,
                ':length_short_by' => $this->data_length - $this->get_param(1)
                )
            )
        );
    }
}
