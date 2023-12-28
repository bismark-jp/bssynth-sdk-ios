//
//  ContentView.swift
//  example2
//
//  Copyright © 2023 bismark LLC. All rights reserved.
//

import SwiftUI
import AVFoundation

struct ContentView: View {
	@State private var program : UInt8 = 0
	@State private var volume : Double = 100.0
	@State private var panpot : Double = 64.0
	@State private var reverb : Double = 40.0
	@State private var chorus : Double = 0.0

	@State private var isNoteOn : Bool = false

	private let bssynth = BssynthDriver.shared
	let channel: UInt8 = 0

	var body: some View {
        ScrollView {
			HStack {
				Text("Program (\(program)): ")
				Spacer()
				Button(action: {
					if 0 < program {
						program -= 1
						bssynth.setChannnelMessage(status: 0xC0 + channel, data1: program, data2: 0x00)
					}
				}) {
					Image(systemName: "minus.circle")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
				.padding(.trailing)
				Button(action: {
					if program < 127 {
						program += 1
						bssynth.setChannnelMessage(status: 0xC0 + channel, data1: program, data2: 0x00)
					}
				}) {
					Image(systemName: "plus.circle")
						.imageScale(.large)
						.foregroundStyle(.tint)
				}
			}
			.padding()

			Button(action: {
				let notes: [UInt8] = [48, 52, 55]
				
				if isNoteOn {
					notes.forEach { note in
						bssynth.setChannnelMessage(status: 0x90 + channel, data1: note, data2: 0)
					}
					isNoteOn = false
				} else {
					notes.forEach { note in
						bssynth.setChannnelMessage(status: 0x90 + channel, data1: note, data2: 100)
					}
					isNoteOn = true
				}
			}) {
				Text(isNoteOn ? "Note Off: C/E/G" : "Note On: C/E/G")
			}
			.padding()
			.accentColor(Color.white)
			.background(isNoteOn ? Color.red : Color.blue)
			.cornerRadius(16)
			
			HStack {
				Text("Volume")
				Spacer()
			}.padding(.horizontal)
			Slider(value: $volume, in: 0...127) { editing in
				bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 0x07, data2: UInt8(volume))
			}
			.padding(.horizontal)

			HStack {
				Text("Panpot")
				Spacer()
			}.padding(.horizontal)
			Slider(value: $panpot, in: 0...127) { editing in
				bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 0x0A, data2: UInt8(panpot))
			}
			.padding(.horizontal)

			HStack {
				Text("Reverb Send")
				Spacer()
			}.padding(.horizontal)
			Slider(value: $reverb, in: 0...127) { editing in
				bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 91, data2: UInt8(reverb))
			}
			.padding(.horizontal)

			HStack {
				Text("Chorus Send")
				Spacer()
			}.padding(.horizontal)
			Slider(value: $chorus, in: 0...127) { editing in
				bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 93, data2: UInt8(chorus))
			}
			.padding(.horizontal)

        }
        .padding()
		.onAppear {
			do {
				let audioSession = AVAudioSession.sharedInstance()
				try audioSession.setCategory(.playback, options: .mixWithOthers)
				try audioSession.setActive(true)
				try audioSession.setPreferredIOBufferDuration(0.005)
			} catch {
				print("AudioSession initialize error")
			}

			bssynth.initialize()
			bssynth.open()
			bssynth.start()
			
			bssynth.setChannnelMessage(status: 0xC0 + channel, data1: program, data2: 0x00)
			bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 0x07, data2: UInt8(volume))
			bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 0x0A, data2: UInt8(panpot))
			bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 91, data2: UInt8(reverb))
			bssynth.setChannnelMessage(status: 0xB0 + channel, data1: 93, data2: UInt8(chorus))
		}
		.onDisappear {
			bssynth.stop()
			bssynth.close()
			bssynth.exit()
		}
    }
}

#Preview {
    ContentView()
}
