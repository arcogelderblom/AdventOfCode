#include <iostream>
#include <chrono>
#include <memory>

#include <cassert>

#include "FileHandler.hpp"
#include "StringParser.hpp"

struct Packet
{
    int typeId = 0;
    int version = 0;
    long value = 0; // if literal
    int lengthTypeId = 0; // if operator
    std::vector<Packet> packets; // if operator
};

std::string toBinaryString(char hexadecimalChar)
{
    switch(hexadecimalChar)
    {
        case ('0'):
            return "0000";
        case ('1'):
            return "0001";
        case ('2'):
            return "0010";
        case ('3'):
            return "0011";
        case ('4'):
            return "0100";
        case ('5'):
            return "0101";
        case ('6'):
            return "0110";
        case ('7'):
            return "0111";
        case ('8'):
            return "1000";
        case ('9'):
            return "1001";
        case ('A'):
            return "1010";
        case ('B'):
            return "1011";
        case ('C'):
            return "1100";
        case ('D'):
            return "1101";
        case ('E'):
            return "1110";
        case ('F'):
            return "1111";
    }
    return "";
}

std::string toBinaryString(std::string hexadecimalString)
{
    std::string result; 
    for (char hexadecimalChar : hexadecimalString)
    {
        result += toBinaryString(hexadecimalChar);
    }
    return result;
}

Packet getPacket(std::string binaryString, int& currentIndex)
{
    int packetVersion = std::stoi(binaryString.substr(currentIndex, 3), 0, 2);
    currentIndex += 3;
    int typeId = std::stoi(binaryString.substr(currentIndex, 3), 0, 2);
    currentIndex += 3;

    Packet packet;
    packet.typeId = typeId;
    packet.version = packetVersion;
    
    if (typeId == 4)
    {
        std::string literalValueString;
        std::string currentGroup = binaryString.substr(currentIndex, 5);
        if (currentGroup[0] == '0')
        {
            currentIndex += 5;
            literalValueString += currentGroup.substr(1);
        }
        else
        {
            while (currentGroup[0] != '0')
            {
                currentGroup = binaryString.substr(currentIndex, 5);
                currentIndex += 5;
                literalValueString += currentGroup.substr(1);
            }
        }
        long literalValue = std::stol(literalValueString, 0, 2);
        
        packet.value = literalValue;
    }
    else
    {
        int lengthTypeId = binaryString[currentIndex] - '0';
        packet.lengthTypeId = lengthTypeId;
        currentIndex++;
        if (lengthTypeId == 0)
        {
            int totalLength = std::stoi(binaryString.substr(currentIndex, 15), 0, 2);
            currentIndex += 15;
            int startIndex = currentIndex;
            while (currentIndex < startIndex + totalLength)
            {
                packet.packets.push_back(getPacket(binaryString, currentIndex));
            }
        }
        if (lengthTypeId == 1)
        {
            int packetsContained = std::stoi(binaryString.substr(currentIndex, 11), 0, 2);
            currentIndex += 11;
            for (int currentPacket = 0; currentPacket < packetsContained; currentPacket++)
            {
                packet.packets.push_back(getPacket(binaryString, currentIndex));
            }
        }
    }
    
    return packet;
}

std::vector<Packet> getPackets(std::string hexadecimalString)
{
    std::vector<Packet> packets;
    int currentIndex = 0;
    std::string binaryString = toBinaryString(hexadecimalString);
    
    while(currentIndex < binaryString.size())
    {
        packets.push_back(getPacket(binaryString, currentIndex));
        if (binaryString.substr(currentIndex).find('1') == std::string::npos)
        {
            // the rest is padding
            currentIndex = binaryString.size();
        }
    }
    return packets;
}

int getVersionSumAllPackets(std::string hexadecimalString)
{
    std::vector<Packet> allPackets = getPackets(hexadecimalString);
    int versionSum = 0;
    for (Packet packet : allPackets)
    {
        versionSum += packet.version;
        std::vector<Packet> packetsToCheck = packet.packets;
        while(!packetsToCheck.empty())
        {
            versionSum += packetsToCheck[0].version;
            for (Packet currentPacket : packetsToCheck[0].packets)
            {
                versionSum += currentPacket.version;
                if (currentPacket.typeId != 4)
                {
                    packetsToCheck.insert(packetsToCheck.end(), currentPacket.packets.begin(), currentPacket.packets.end());
                }
            }
            packetsToCheck.erase(packetsToCheck.begin());
        }
    }
    return versionSum;
}

long getPacketValue(Packet packet)
{
    if (packet.typeId == 4)
    {
        return packet.value;
    }

    long value = 0;
    switch (packet.typeId)
    {
        case 0:
        {
            std::for_each(packet.packets.begin(), packet.packets.end(), [&](Packet p){ value += getPacketValue(p); });
            break;
        }
        case 1:
        {
            value = 1;
            std::for_each(packet.packets.begin(), packet.packets.end(), [&](Packet p){ value *= getPacketValue(p); });
            break;
        }
        case 2:
        {
            std::vector<long> packetValues;
            std::for_each(packet.packets.begin(), packet.packets.end(), [&](Packet p){ packetValues.push_back(getPacketValue(p)); });
            std::sort(packetValues.begin(), packetValues.end());
            value = *packetValues.begin();
            break;
        }
        case 3:
        {
            std::vector<long> packetValues;
            std::for_each(packet.packets.begin(), packet.packets.end(), [&](Packet p){ packetValues.push_back(getPacketValue(p)); });
            std::sort(packetValues.begin(), packetValues.end());
            value = *packetValues.rbegin();
            break;
        }
        case 5:
        {
            value = getPacketValue(packet.packets[0]) > getPacketValue(packet.packets[1]) ? 1 : 0;
            break;
        }
        case 6:
        {
            value = getPacketValue(packet.packets[0]) < getPacketValue(packet.packets[1]) ? 1 : 0;
            break;
        }
        case 7:
        {
            value = getPacketValue(packet.packets[0]) == getPacketValue(packet.packets[1]) ? 1 : 0;
            break;
        }
    }

    return value;
}

int main(void)
{
    std::string testInput1 = "8A004A801A8002F478";
    std::string testInput2 = "620080001611562C8802118E34";
    std::string testInput3 = "C0015000016115A2E0802F182340";
    std::string testInput4 = "A0016C880162017C3686B18A3D4780";
    assert(getVersionSumAllPackets(testInput1) == 16);
    assert(getVersionSumAllPackets(testInput2) == 12);
    assert(getVersionSumAllPackets(testInput3) == 23);
    assert(getVersionSumAllPackets(testInput4) == 31);
    
    FileHandler fileHandler("input-files/2021/day16.txt");
    std::string input = StringParser::toVector(fileHandler.getBuffer(), "\n")[0];
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 16, puzzle 1: " << std::flush << getVersionSumAllPackets(input)  << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    std::string testInput5 = "C200B40A82";
    std::string testInput6 = "04005AC33890";
    std::string testInput7 = "880086C3E88112";
    std::string testInput8 = "CE00C43D881120";
    std::string testInput9 = "D8005AC2A8F0";
    std::string testInput10 = "F600BC2D8F";
    std::string testInput11 = "9C005AC2F8F0";
    std::string testInput12 = "9C0141080250320F1802104A08";
    
    assert(getPacketValue(getPackets(testInput5)[0]) == 3);
    assert(getPacketValue(getPackets(testInput6)[0]) == 54);
    assert(getPacketValue(getPackets(testInput7)[0]) == 7);
    assert(getPacketValue(getPackets(testInput8)[0]) == 9);
    assert(getPacketValue(getPackets(testInput9)[0]) == 1);
    assert(getPacketValue(getPackets(testInput10)[0]) == 0);
    assert(getPacketValue(getPackets(testInput11)[0]) == 0);
    assert(getPacketValue(getPackets(testInput12)[0]) == 1);
    
    t_begin = std::chrono::high_resolution_clock::now();    
    std::cout << "Day 16, puzzle 2: " << std::flush << getPacketValue(getPackets(input)[0]) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}
