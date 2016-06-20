// Code to test com between AWS and Particle Photon


void setup() {
  Particle.function("webFunc", webFuncCallback, this);
  Serial.begin(115200);
}

void loop() {

}

int webFuncCallback(String command){
    Serial.println(command);
    String subCommand;
    String commandResults;
    uint8_t length = command.length();
    Serial.println("command Length: " + String(length));
    int multipleCommands = 0;
    int i;
    for(i = 0; i<length;i++){
        multipleCommands = command.indexOf(':');
        if(multipleCommands != -1){
            subCommand = command.substring(0, multipleCommands);
            command.remove(0, multipleCommands+1);
        } else {
            subCommand = command;
        }
        Serial.println(subCommand);
//        Serial.println(String(multipleCommands));

        if(subCommand.startsWith("G")){
            subCommand.remove(0, 1);
            if(subCommand.startsWith("FAS")){
                commandResults.concat("FAS50:");
            } else if(subCommand.startsWith("RHU")){
                commandResults.concat("RHU23:");
            } else if(subCommand.startsWith("TMP")){
                commandResults.concat("TMP72:");
            } else if(subCommand.startsWith("WTL")){
                commandResults.concat("WTL42:");
            } else if(subCommand.startsWith("WTF")){
                commandResults.concat("WTF0:");
            } else if(subCommand.startsWith("RLV")){
                commandResults.concat("RLV81:");
            } else if(subCommand.startsWith("POW")){
                commandResults.concat("POW1:");
            } else if(subCommand.startsWith("MOD")){
                commandResults.concat("MOD9:");
            } else if(subCommand.startsWith("SET")){
                commandResults.concat("SET245:");
            } else if(subCommand.startsWith("TTE")){
                commandResults.concat("TTT324:");
            } else if(subCommand.startsWith("TTT")){
                commandResults.concat("TTT24:");
            } else if(subCommand.startsWith("BRT")){
                commandResults.concat("BRT100:");
            } else if(subCommand.startsWith("TRS")){
                commandResults.concat("TRS30:");
            } else {
                // Error Unrecognized Command
                commandResults.concat(subCommand);
                commandResults.concat("ERR:");
            }

        } else if(subCommand.startsWith("S")){
            subCommand.remove(0,1);
            if(subCommand.startsWith("FAS")){
                subCommand.remove(0,3);
                Serial.println("Fan speed " + subCommand);
                commandResults.concat("FAS");
                commandResults.concat(subCommand);
                commandResults.concat(':');
            } else if(subCommand.startsWith("POW")){
                subCommand.remove(0,3);
                Serial.println("Power " + subCommand);
                commandResults.concat("POW");
                commandResults.concat(subCommand);
            } else if(subCommand.startsWith("MOD")){
                subCommand.remove(0,3);
                Serial.println("Mode " + subCommand);
                commandResults.concat("MOD");
                commandResults.concat(subCommand);
                commandResults.concat(':');
            } else if(subCommand.startsWith("SET")){
                subCommand.remove(0,3);
                Serial.println("Setting " + subCommand);
                commandResults.concat("SET");
                commandResults.concat(subCommand);
                commandResults.concat(':');
            } else if(subCommand.startsWith("BRT")){
                subCommand.remove(0,3);
                Serial.println("Brightness " + subCommand);
                commandResults.concat("BRT");
                commandResults.concat(subCommand);
                commandResults.concat(':');
            } else if(subCommand.startsWith("TRS")){
                subCommand.remove(0,3);
                Serial.println("Transducer Setting " + subCommand);
                commandResults.concat("TRS");
                commandResults.concat(subCommand);
                commandResults.concat(':');
            } else {
                // Error Unrecognized Command
                commandResults.concat(subCommand);
                commandResults.concat("ERR:");
            }
        } else {
            // Error Unrecognized command
            commandResults.concat(subCommand);
            commandResults.concat("ERR:");
        }

        if(multipleCommands == -1){
            commandResults.remove(commandResults.length()-1);
            Serial.println("Commands Done");
            Serial.println(commandResults);
            Particle.publish("deviceData", commandResults);
            return 1;
        }
    }
}
