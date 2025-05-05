cmd_/home/tejsaw/drivers/simple_driver.mod := printf '%s\n'   simple_driver.o | awk '!x[$$0]++ { print("/home/tejsaw/drivers/"$$0) }' > /home/tejsaw/drivers/simple_driver.mod
