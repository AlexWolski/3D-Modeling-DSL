number numRooms = 3;
number numStories = 2;

model room
{
	-- Left Wall --
	box();
	color(0, 0, 0);
	scale(0, 0.95, 0);
	translate(-50, 0, 0);

	-- Right Wall --
	box();
	color(0, 0, 0);
	scale(0.05, 0.95, 0.95);
	translate(50, 0, 0);

	-- Back Wall --
	box();
	color(1, 1, 1);
	scale(1.05, 1.05, 0.05);
	translate(0, 0, -50);

	-- Floor Wall --
	box();
	color(0, 0, 0);
	scale(1.05, 0.05, 0.95);
	translate(0, -50, 0);

	-- Cieling Wall --
	box();
	color(0, 0, 0);
	scale(1.05, 0.05, 0.95);
	translate(0, 50, );
}

model house
{
	number currentStory = 0;

	while (currentStory < numStories)
	{
		number currentRoom = 0;

		while (currentRoom < numRooms)
		{
			room();
			float roomOffset = 100 * currentRoom;
			translate(roomOffset, 0, 0);
		}
	}
}