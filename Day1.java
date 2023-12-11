package Day1;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;

public class Day1 {
	
	static int part1 = 9;
	static int part2 = 19;
	static String[] possible = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	static int[] numerical = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
	public static void main(String[] args) {
		try{
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("src/Day1/day1input.txt")));
			String line = br.readLine();
			int sum = 0;
			while(line != null){
				sum += getValue(line);
				line = br.readLine();
			}
			System.out.println(sum);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	public static int getValue(String line){
		int minIndex = Integer.MAX_VALUE;
		int maxIndex = Integer.MIN_VALUE;
		int ind1 = -1;
		int ind2 = -1;
		
		for(int i =0; i<part2; i++){
			int index1 = line.contains(possible[i]) ? line.indexOf(possible[i]) : Integer.MAX_VALUE;
			int index2 = line.contains(possible[i]) ? line.lastIndexOf(possible[i]) : Integer.MIN_VALUE;
			if(index1 < minIndex){
				ind1 = i;
				minIndex = index1;
			}
			if(index2 > maxIndex){
				ind2 = i;
				maxIndex = index2;
			}
		}
		int first = numerical[ind1];;
		int last = numerical[ind2];
		String concat = first + "" + last;
		return Integer.parseInt(concat);
	}
}
