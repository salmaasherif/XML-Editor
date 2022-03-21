#include "xmlconsistency.h"
#include "label.h"

std::string output;

std::vector<std::string> xml_corrector(std::vector<std::string>& xml_file)
{

	int bars_repetition = 0;
	int bars_num = xml_file.size();
	std::vector<std::string> mistakes_discovered;
	std::string bar;
	std::stack<labels> gatherer;

	//to check for repeated files
	while (bars_repetition < bars_num)
	{
		bar = xml_file[bars_repetition];
		int key_repetition = 0;
		//to check for repeated lines
		while (bar[key_repetition] != '\0')
		{
			if (bar[key_repetition] == '<')
			{
				std::string label;
				if (bar[key_repetition + 1] == '/')
				{
					key_repetition = key_repetition + 2;
					while (bar[key_repetition - 1] != '>')
					{
						label.push_back(bar[key_repetition++]);
					}
				CheckOnlabel:
					if (!gatherer.empty())
					{
						if (label == (gatherer.top()).features)
						{
							gatherer.pop();
						}
						else
						{
							bool absentOpenTag = 1;
							std::stack<labels> temporaryGatherer = gatherer;
							temporaryGatherer.pop();
							while (!(temporaryGatherer.empty()))
							{
								//check if the absent tag is a closing one
								if (label == ((temporaryGatherer.top()).features))
								{
									//corrects the absent closing tag
									labels temporaryLabel = gatherer.top();
									gatherer.pop();
									std::string temporaryBar = xml_file[temporaryLabel.bar];
									temporaryLabel.features = "</" + temporaryLabel.features;
									temporaryBar.insert(temporaryLabel.margin, temporaryLabel.features);
									xml_file[temporaryLabel.bar] = temporaryBar;



									//prints the error to the GUI window
									mistakes_discovered.push_back("Closing tag is not found" + temporaryLabel.features + "\r\n");
									absentOpenTag = 0;
									goto CheckOnlabel;
								}
								temporaryGatherer.pop();
							}
							if (absentOpenTag == 1)
							{
								//corrects the missing opening tag
								labels temporaryLabel = gatherer.top();
								std::string temporaryBar = xml_file[temporaryLabel.bar];
								label = "<" + label;
								temporaryBar.insert(temporaryLabel.margin, label);
								xml_file[temporaryLabel.bar] = temporaryBar;

								//prints the error to the GUI window
								mistakes_discovered.push_back("Opening tag is not found" + label + "\r\n");
							}
						}
					}
					else
					{
						//while the stack is empty, correct the absent opening tags
						std::string temporaryBar = xml_file[0];
						label = "<" + label;
						temporaryBar.insert(0, label);
						xml_file[0] = temporaryBar;

						//prints the error to the GUI window
						mistakes_discovered.push_back("Opening tag is not found" + label + "\r\n");
					}
				}
				else
				{
					if (bar[key_repetition + 1] != '?')
					{
						//pushes the opening tag onto the stack with its data
						labels *ptr;
						key_repetition = key_repetition + 1;
						while (bar[key_repetition - 1] != '>')
						{
							if (bar[key_repetition] == ' ')
							{
								label.push_back('>');
								break;
							}
							label.push_back(bar[key_repetition++]);
						}

						ptr = new labels(label, bars_repetition, key_repetition);
						gatherer.push(*ptr);
					}
					else
					{
						break;
					}

				}
			}
			else
			{
				key_repetition++;
			}
		}
		bars_repetition++;
	}
	//correcting the absent closing tags in the stack
	while (!(gatherer.empty()))
	{
		//correcting the absent closing tags
		std::string temporaryLabel = (gatherer.top()).features;
		gatherer.pop();
		temporaryLabel = "</" + temporaryLabel;
		xml_file.push_back(temporaryLabel);

		//prints the error to the GUI window
		mistakes_discovered.push_back("Closing tag is not found " + temporaryLabel + "\r\n");

	}
	//a vector with all the mistakes discovered in the xml file
	return mistakes_discovered;
}