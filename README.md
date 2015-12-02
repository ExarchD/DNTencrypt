# DNTencrypt

DNTecrypt is an encryption chat service. It works on a server client method, where the server essentially knows nothing. The server recieves hashes and ecrypted messages but no other details from the client. Clients pull messages from the server using the commonly calculated hashes. Encryption is done using the Pretty Good Privacy protocol though GPG. 

One of the main goals of this project, besides self-education, is to further spread the use of gpg keys. Encryption today is cheap and powerful. Why is it acceptable to send anything into the internet without some layer of privacy? The most commonly used chat clients are open and visible to servers. In my mind, there is no good reason to allow that.

This project is not perfect, ip addresses could still be tracked, and if someone gets access to a participant's private key, and entire conversation can be viewed. Perhaps a tor service would allow masking of ip addresses. As for key protection, that is up to the user. Take appropriate precautions. Here the same rules apply as for general gpg use, you can read more online regarding this. 


#Installation
Installing on Ubuntu (12.04):

qmake:

sudo apt-get install qtdeclarative5-dev

sudo apt-get install build-essential

git clone https://github.com/ExarchD/DNTencrypt.git

cd DNTencrypt

mkdir build; cd build

cmake ..

make

make install

#Doxygen

http://exarchd.github.io/DNTencrypt/


#TODO

Set configure directory appropriately in UNIX and in WINDOWS

Conversation logging using sql databases.
