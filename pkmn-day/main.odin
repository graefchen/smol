package main

import "core:time"
import "core:fmt"

getSeason :: proc(month: int) -> (season: int) {
	return ((month - 1) % 4)
}

getDayTime :: proc(season: int, hour: int) -> (daytime: u8) {
	time := [96]u8{
		0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,0,0,0,0,
		0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,0,0,0,
		0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,0,0,0,0,
		0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,3,3,0,0,0,0,0
	}
	return time[(season * 24) + hour]
}

main :: proc() {
	now := time.now()
	month := time.month(now)
	hour, _, _ := time.clock_from_time(now)

	seasons:= []string{"spring", "summer", "autumn", "winter"};
	daytime:= []string{"night", "morning", "day", "evening"};

	fmt.printf("%s, %s\n",
		seasons[getSeason(int(month))],
		daytime[getDayTime(getSeason(int(month)), hour)]
	);
}
