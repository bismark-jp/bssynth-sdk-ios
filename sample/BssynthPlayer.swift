//
//  BssynthPlayer.swift
//  sample
//
//  Copyright © 2020 bismark LLC. All rights reserved.
//

import Foundation

class BssynthPlayer {

    static let shared: BssynthPlayer = {
        let instance = BssynthPlayer()
        return instance
    }()

    private let api = bsmpLoad()!
    private var handle: BSMP_HANDLE? = nil

    public func initialize() {
        let library = Bundle.main.path(forResource: "GeneralUser GS SoftSynth v1.44", ofType: "sf2")!

        let err = api.pointee.initializeWithSoundLib(
            &handle,
            { handle, type, data, user in
                switch type {
                    case BSMP_CALLBACK_TYPE_OPEN:
                        print("opened")
                    case BSMP_CALLBACK_TYPE_CLOSE:
                        print("closeed")
                    case BSMP_CALLBACK_TYPE_START:
                        print("started")
                    case BSMP_CALLBACK_TYPE_STOP:
                        print("stopped")
                    case BSMP_CALLBACK_TYPE_SEEK:
                        print("seeked")
                    case BSMP_CALLBACK_TYPE_CLOCK:
                        BssynthPlayer.shared.clocks += 1
                    case BSMP_CALLBACK_TYPE_TEMPO:
                        let tempo = unsafeBitCast(data, to: UnsafePointer<UInt32>.self).pointee
                        print("tempo = \(tempo)[usec/beat]")
                    case BSMP_CALLBACK_TYPE_TIME_SIGNATURE:
                        let signature = unsafeBitCast(data, to: UnsafePointer<UInt32>.self).pointee
                        print("set time signature = \(signature)")
                    /*
                    case BSMP_CALLBACK_TYPE_CHANNEL_MESSAGE:
                        let msg = unsafeBitCast(data, to: UnsafeMutablePointer<UInt32>.self).pointee
                        let status = UInt8((msg >> 16) & 0x000000FF)
                        let data0 = UInt8((msg >> 8) & 0x000000FF)
                        let data1 = UInt8((msg >> 0) & 0x000000FF)
                    */
                    default:
                        break
                }
            },
            nil, // pointer for callback (not used here)
            library.cString(using: .utf8),
            nil,
            bssynth_key
        )

        if err != BSMP_OK {
            print("ERROR - initialize synthesizer")
        }
    }

    public func exit() {
        if api.pointee.exit(handle) != BSMP_OK {
            print("ERROR - finilize synthesizer")
        }
    }
    
    public func set(file: String) {
        let path = file.cString(using: .utf8)
        if api.pointee.setFile(handle, path) != BSMP_OK {
            print("ERROR - set file")
        }
    }

    public func open() {
        if api.pointee.open(handle, nil, nil) != BSMP_OK {
            print("ERROR - open")
        }
    }

    public func close() {
        if api.pointee.close(handle) != BSMP_OK {
            print("ERROR - close")
        }
    }

    public func start() {
        if api.pointee.start(handle) != BSMP_OK {
            print("ERROR - start")
        }
    }

    public func stop() {
        if api.pointee.stop(handle) != BSMP_OK {
            print("ERROR - stop")
        }
    }

    public var isPlaying: Bool {
        return api.pointee.isPlaying(handle) == 1
    }

    public var clocks: Int = 0
    public var division: UInt16 = 480

    public var key: Int {
        set {
            print("set key = \(newValue)")
            var value = Int32(newValue)
            if api.pointee.ctrl(handle, BSMP_CTRL_SET_MASTER_KEY, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - set key = \(newValue)")
            }
        }
        get {
            var value = 0
            if api.pointee.ctrl(handle, BSMP_CTRL_GET_MASTER_KEY, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - get key")
            }
            return Int(value)
        }
    }
    public var speed: Int {
        set {
            print("set speed = \(newValue)")
            var value = Int32(newValue)
            if api.pointee.ctrl(handle, BSMP_CTRL_SET_SPEED, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - set speed = \(newValue)")
            }
        }
        get {
            var value = 0
            if api.pointee.ctrl(handle, BSMP_CTRL_GET_SPEED, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - get speed")
            }
            return Int(value)
        }
    }

    public var reverb: Bool {
        set {
            print("set reverb = \(newValue)")
            var value: Int32 = newValue ? 1 : 0
            if api.pointee.ctrl(handle, BSMP_CTRL_SET_REVERB, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - set reverb = \(newValue)")
            }
        }
        get {
            var value = 0
            if api.pointee.ctrl(handle, BSMP_CTRL_GET_REVERB, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - get reverb")
            }
            return value == 1
        }
    }
    public var chorus: Bool {
        set {
            print("set chorus = \(newValue)")
            var value: Int32 = newValue ? 1 : 0
            if api.pointee.ctrl(handle, BSMP_CTRL_SET_CHORUS, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - set chorus = \(newValue)")
            }
        }
        get {
            var value = 0
            if api.pointee.ctrl(handle, BSMP_CTRL_GET_CHORUS, &value, value.byteWidth) != BSMP_OK {
                print("ERROR - get chorus")
            }
            return value == 1
        }
    }

    public func seek(clock: UInt) {
        print("seek = \(clock)")
        clocks = 0
        let tick = clock * UInt(division) / 24
        if api.pointee.seek(handle, tick) != BSMP_OK {
            print("ERROR - seek = \(clock)")
        }
    }

    public func totalClocks() -> Int {
        var totaltick: UInt = 0
        if api.pointee.getFileInfo(handle, nil, &division, &totaltick, nil) != BSMP_OK {
            print("ERROR - getFileInfo")
        }
        return Int(totaltick * 24) / Int(division)
    }

    public func bounce() {
        guard !isPlaying else {
            print("ERROR - bounce can not be done during playback")
            return
        }
        
        let root = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)[0]
        let path = root + "/bounced.wav"
        if api.pointee.bounce(
            handle,
            path.cString(using: .utf8),
            BSMP_WAVE_FILE_RIFF,
            { percent, user in
                print("bouncing... \(percent)")
                return 0
            },
            nil // pointer for callback (not used here)
        ) != BSMP_OK {
            print("ERROR - bounce")
        } else {
            print("bounce completed at \(path)")
        }
    }
}

extension FixedWidthInteger {
    var byteWidth: Int32 {
        return Int32(self.bitWidth / UInt8.bitWidth)
    }

    static var byteWidth: Int32 {
        return Int32(Self.bitWidth / UInt8.bitWidth)
    }
}
