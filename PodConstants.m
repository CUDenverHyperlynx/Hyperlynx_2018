% Use this program to set constants in the PodConstants.mat file.
%
% INSTRUCTIONS:
%   Change variable values, or add new variables.  Include units in name 
%   of variable.
%
clear all; clc;

%   Use this code if you need to delete a variable from the file.  There is
%   no way to delete only one variable.
%
% if exist('PodConstants.mat','file')
%     delete('PodConstants.mat')
% end
% save('PodConstants');
%

pod_mass_lbs = 650;
pod_mass_kg = pod_mass_lbs / 2.2;
wheel_base_in = 78;
wheel_radius_in = 11.5;
design_maxspeed_mph = 250;


% This line saves data to the .mat file, and overwrites existing values.
save('PodConstants','-append');