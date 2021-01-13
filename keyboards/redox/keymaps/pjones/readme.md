# Pete's Redox Keymap

## Initial Set Up

  * Pro-micro boards:

        nix-shell --run 'env BOOTLOADER=caterina make redox:pjones:avrdude-split-left'

## Flashing

  * Regular pro-micro boards:

        nix-shell --run 'env BOOTLOADER=caterina make redox:pjones:avrdude'

  * For boards with an Elite-C board:


        nix-shell --run 'sudo env BOOTLOADER=atmel-dfu make redox:pjones:dfu'
