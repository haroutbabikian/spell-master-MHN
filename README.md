# spell-master-MHN
Implementation of our spell master game.

Please paste the following command in your terminal for compilation:
`gcc -o spell_master_game src/main.c src/game_logic.c src/user_input.c src/file_operations.c src/winner_determination.c src/bot.c -I./include`

Testing(unstable/alpha): -Warning: Alters spells.txt and adds multiple txt files
Please paste the following command in your terminal for compilation:
`gcc -o test_program src/testing.c src/game_logic.c src/user_input.c src/file_operations.c src/winner_determination.c src/bot.c -I./include`