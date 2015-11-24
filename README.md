# emesh_system

The commands to install all of the code necessary for this project are below:
git clone https://github.com/nairgroup/emesh_system
cd emesh_system
sudo chmod 777 setup_emesh
sudo ./setup_emesh

To run the driver software:
cd emesh_driver
sudo python emesh_driver.py #The sudo is necessary to utilize the GPIO library in the driver code


Just use run the setup_emesh script to install the necessary libraries.
Then cd into the emesh_driver directory and use "git pull" to update the driver software.
