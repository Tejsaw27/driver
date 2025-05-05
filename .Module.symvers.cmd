cmd_/home/tejsaw/drivers/Module.symvers :=  sed 's/ko$$/o/'  /home/tejsaw/drivers/modules.order | scripts/mod/modpost -m      -o /home/tejsaw/drivers/Module.symvers -e -i Module.symvers -T - 
