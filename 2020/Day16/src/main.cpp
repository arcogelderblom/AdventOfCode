#include <iostream>

#include "FileHandler.hpp"
#include "StringParser.hpp"

#include "TicketProcessor.hpp"

int main(void) {
    FileHandler fileHandler("input-files/2020/day16.txt");
    std::vector<std::string> input = StringParser::toVector(fileHandler.getBuffer(), "\n\n");
    
    std::vector<std::string> rules;
    while(input[0].find('\n') != std::string::npos) {
        rules.push_back(input[0].substr(0, input[0].find('\n')));
        input[0] = input[0].substr(input[0].find('\n') + 1);
    }
    rules.push_back(input[0]);
    
    std::string ownTicketString = input[1].substr(input[1].find('\n') + 1);
    std::vector<int> ownTicket;
    while (ownTicketString.find(',') != std::string::npos) {
        ownTicket.push_back(std::stoi(ownTicketString.substr(0, ownTicketString.find(','))));
        ownTicketString = ownTicketString.substr(ownTicketString.find(',')+1); 
    }
    ownTicket.push_back(std::stoi(ownTicketString));

    std::string nearbyTicketsString = input[2].substr(input[2].find('\n') + 1);
    std::vector< std::string > nearbyTicketsStrings;
    while (nearbyTicketsString.find('\n') != std::string::npos) {
        nearbyTicketsStrings.push_back(nearbyTicketsString.substr(0, nearbyTicketsString.find('\n')));
        nearbyTicketsString = nearbyTicketsString.substr(nearbyTicketsString.find('\n')+1); 
    }
    nearbyTicketsStrings.push_back(nearbyTicketsString);

    std::vector< std::vector<int> > nearbyTickets;
    for (std::string nearbyTicket : nearbyTicketsStrings) {
        std::vector<int> tmp;
        while (nearbyTicket.find(',') != std::string::npos) {
            tmp.push_back(std::stoi(nearbyTicket.substr(0, nearbyTicket.find(','))));
            nearbyTicket = nearbyTicket.substr(nearbyTicket.find(',')+1); 
        }
        tmp.push_back(std::stoi(nearbyTicket));
        nearbyTickets.push_back(tmp);
    }

    TicketProcessor processor(rules);
    std::cout << "Puzzle one output: " << processor.getTicketScanningErrorRate(nearbyTickets) << std::endl;
    processor.determineFields(nearbyTickets);
    std::cout << "Puzzle two output: " << processor.getMultiplicationDeparture(ownTicket) << std::endl;
}
