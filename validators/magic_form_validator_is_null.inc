<?php

class magic_form_validator_is_null extends magic_form_validator implements magic_form_validator_interface
{
    public function test($data)
    {
        return trim($data) == null;
    }

    public function user_friendly_failure_message($message_params)
    {
        return t("Field must be empty");
    }
}
