package Day5;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;

public class Day5 {
	public static void main(String[] args) {
		try{
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("src/Day5/day5input.txt")));
			String seedLine = br.readLine();
			seedLine = seedLine.substring(seedLine.indexOf(":") + 2);
			String[] seedsStrings = seedLine.split(" ");
			long[] seeds = new long[seedsStrings.length];
			for(int i =0; i< seedsStrings.length; i++){seeds[i] = Long.parseLong(seedsStrings[i]);}
			br.readLine();
			ArrayList<ArrayList<long[]>> maps = new ArrayList<>();
			ArrayList<long[]> curr = new ArrayList<>();
			String line = br.readLine();
			while(line != null){
				if(line.trim().equals("")){
					if(!curr.isEmpty()){
						maps.add(curr);
					}
				}
				else if(line.endsWith(":")){
					curr = new ArrayList<>();
				}
				else{
					String[] numbers = line.split(" ");
					long destStart = Long.parseLong(numbers[0]);
					long sourceStart = Long.parseLong(numbers[1]);
					long range = Long.parseLong(numbers[2]);
					curr.add(new long[]{destStart, sourceStart, range});
				}
				line = br.readLine();
			}
			if(!curr.isEmpty()){
				maps.add(curr);
			}
			
			long minLocation = Long.MAX_VALUE;
			for(long seed: seeds){
				long currVal = seed;
				for(ArrayList<long[]> map: maps){
					for(long[] range: map){
						if(range[1] <= currVal && range[1]+range[2] > currVal){
							currVal = range[0] + (currVal - range[1]);
							break;
						}
					}
				}
				minLocation = Math.min(minLocation, currVal);
			}
			System.out.println(minLocation);
			
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}
