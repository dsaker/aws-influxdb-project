variable "home_ip" {
  description = "This is your home ip where sensor data will be sent from"
  type        = string
  sensitive   = true
}

variable "key_pair_name" {
  description = "This is the name of your ssh pair key"
  type        = string
}