# Pete's Redox Keymap

## Flashing

  * Regular pro-micro boards:

        nix-shell --run 'env BOOTLOADER=caterina make redox:pjones:avrdude'

  * For boards with an Elite-C board:


        nix-shell --run 'env BOOTLOADER=atmel-dfu make redox:pjones:dfu'
