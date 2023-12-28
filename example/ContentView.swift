//
//  ContentView.swift
//  example
//
//  Copyright © 2023 bismark LLC. All rights reserved.
//

import SwiftUI
import AVFoundation

struct ContentView: View {
	
	@State private var clocks : Double = 0
	@State private var totalClocks : Int = 0
	@State private var isEditing : Bool = false

	@State private var key : Int = 0
	@State private var speed : Int = 0

	private let bssynth = BssynthPlayer.shared

    var body: some View {
        VStack {
			HStack {
				Button(action: {
					if !bssynth.isPlaying {
						bssynth.start()
					}
				}) {
					Image(systemName: "play")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
				.padding(.trailing)
				Button(action: {
					if bssynth.isPlaying {
						bssynth.stop()
					}
				}) {
					Image(systemName: "pause")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
				Spacer()
			}
			.padding()

			Slider(value: $clocks, in: 0...Double(totalClocks)) { editing in
				isEditing = editing
				if (!editing) {
					bssynth.seek(clock: UInt(clocks))
				}
			}
			.padding(.horizontal)

			HStack {
				Text("Key Control (\(key)): ")
				Spacer()
				Button(action: {
					if -5 < key {
						key -= 1
						bssynth.key = key
					}
				}) {
					Image(systemName: "minus.circle")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
				.padding(.trailing)
				Button(action: {
					if key < 5 {
						key += 1
						bssynth.key = key
					}
				}) {
					Image(systemName: "plus.circle")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
			}
			.padding()

			HStack {
				Text("Speed Control (\(speed)): ")
				Spacer()
				Button(action: {
					if -8 < speed {
						speed -= 1
						bssynth.speed = speed
					}
				}) {
					Image(systemName: "minus.circle")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
				.padding(.trailing)
				Button(action: {
					if speed < 8 {
						speed += 1
						bssynth.speed = speed
					}
				}) {
					Image(systemName: "plus.circle")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
			}
			.padding()

			Spacer()
        }
        .padding()
		.onAppear {
			do {
				let audioSession = AVAudioSession.sharedInstance()
				try audioSession.setCategory(.playback)
				try audioSession.setActive(true)
			} catch {
				print("AudioSession initialize error")
			}

			bssynth.initialize()
			
			// set midi contents
			let path = Bundle.main.path(forResource: "sample", ofType: "mid")!
			bssynth.set(file: path)
			
			totalClocks = bssynth.totalClocks()

			// open wave output device
			bssynth.open()

			// enable timer to update seek slider position
			Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) { timer in
				if !isEditing {
					clocks = Double(bssynth.clocks)
				}
			}
		}
		.onDisappear {
			bssynth.close()
		}
    }
}

#Preview {
    ContentView()
}
