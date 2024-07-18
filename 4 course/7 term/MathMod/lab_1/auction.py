import os

from random_generator import generator

class Auction:
    def __init__(self):
        self.auction_list = []
        self.coeff_list = []
    
    def start(self):
        while True:
            option = int(input("Chose an option:\n1. Add the game\n2. Get gamelist\n3. Start the roulette\n4. Clean the lists\n5. Exit\n\nOption: "))
            os.system('clear')
            
            match option:
                case 1:
                    self.add_donate()
                case 2:
                    self.get_gamelist()    
                case 3:
                    self.choose_the_game()
                case 4:
                    self.clean_lists()
                case 5:
                    print("Bye!")
                    return 0
            input()
            os.system('clear')
                    
    def add_donate(self):
        game_str = str(input("Enter the game name: "))
        donate_str = float(input("Enter the donate: "))
        
        if game_str in self.auction_list:
            self.coeff_list[self.auction_list.index(game_str)] += donate_str
        else:
            self.auction_list.append(game_str)
            self.coeff_list.append(donate_str)

    def get_gamelist(self):
        print("--- List of games ---")
        for i in range(0, len(self.auction_list)):
            print(f"\nGame: {self.auction_list[i]}\nCoeff: {self.coeff_list[i]}")
    
    def choose_the_game(self):
        chose = generator(self.auction_list, self.coeff_list)
        print(f"Winner: {chose}\n")
    
    def clean_lists(self):
        self.auction_list = []
        self.coeff_list = []