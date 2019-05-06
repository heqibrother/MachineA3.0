#include "handlecontrol.h"

HandleCommand handle_command;

void SendFieldParaY()
{
		SendFieldPara1((short)MyClose(current_field.first_line_position.y),
	                 (short)MyClose(current_field.first_rope_position.y),
	                (short)MyClose(current_field.second_rope_position.y),
	                 (short)MyClose(current_field.hill_position.y));
}
