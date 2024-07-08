data "aws_ami" "ubuntu" {
  most_recent = true

  filter {
    name   = "name"
    values = ["ubuntu/images/hvm-ssd/ubuntu-jammy-22.04-amd64-server-*"]
  }

  filter {
    name   = "virtualization-type"
    values = ["hvm"]
  }

  owners = ["099720109477"] # Canonical
}

resource "aws_instance" "influx_instance" {
  ami                         = data.aws_ami.ubuntu.id
  instance_type               = "t2.micro"
#  vpc_id                   = "vpc-b9a486c3"
  associate_public_ip_address = true
  key_name = var.key_pair_name

  tags = {
    "Name" = "influx"
  }

  vpc_security_group_ids = [
    aws_security_group.influx_sg.id
  ]
}

resource "aws_eip" "influx_ip" {
  vpc = true
  instance = aws_instance.influx_instance.id
  tags = {
    "Name" = "influx-ip"
  }
}

resource "aws_security_group" "influx_sg" {
  description = "ec2 instance with influxdb"
#  vpc_id      = "vpc-b9a486c3"
  egress = [{
    cidr_blocks      = ["0.0.0.0/0"]
    description      = ""
    from_port        = 0
    ipv6_cidr_blocks = []
    prefix_list_ids  = []
    protocol         = "-1"
    security_groups  = []
    self             = false
    to_port          = 0
  }]
  ingress = [{
    "cidr_blocks": ["0.0.0.0/0"],
    "description": "",
    "from_port": 443,
    "ipv6_cidr_blocks": [],
    "prefix_list_ids": [],
    "protocol": "tcp",
    "security_groups": [],
    "self": false,
    "to_port": 443
    },
    {
    cidr_blocks      = ["${var.home_ip}/32"]
    description      = ""
    from_port        = 22
    ipv6_cidr_blocks = []
    prefix_list_ids  = []
    protocol         = "tcp"
    security_groups  = []
    self             = false
    to_port          = 22
    }
  ]
  name                   = "influxdb"
  name_prefix            = null
  revoke_rules_on_delete = null
  tags = {
    Name = "Influx"
  }
  tags_all = {
    Name = "Influx"
  }
  timeouts {
    create = null
    delete = null
  }
}

output "public_dns" {
  value = aws_instance.influx_instance.public_dns
}

#output "public_ip" {
#  value = aws_instance.influx.public_ip
#}

output "eip" {
  value = aws_eip.influx_ip.public_ip
}